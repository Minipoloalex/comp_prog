import Text.Read (read)
import Data.List (span)
import Data.Char (isDigit, isSpace)

main :: IO ()
main = do
    lines <- getLines
    if lines == [] then do
        return ()
    else do
        let s = round $ (processResult $ processLines lines)
        putStrLn $ show s ++ "%"
        main



getLines :: IO [String]
getLines = do
    l <- getLine
    let line = filter (not . isSpace) l
    if line == "-" then do
        return []
    else do
        otherLines <- getLines
        return (line:otherLines)

-- These should probably be synonyms of Ints and not data types
data Grams a = Grams a deriving Show
data Percent a = Percent a deriving Show
data Calories a = Calories a deriving Show
data Amount a = Amount (Grams a) (Percent a) (Calories a) deriving Show

getPercentage :: Amount Int -> Int
getPercentage (Amount _ (Percent p) _) = p

getTotalCalories :: (Amount Int, Int) -> Int
getTotalCalories (Amount (Grams g) _ (Calories c), gramsRatio) = g * gramsRatio + c

type Fat a = Amount a
type Protein a = Amount a
type Starch a = Amount a
type Sugar a = Amount a
type Alcohol a = Amount a
-- Probably a better idea would be to make this a list, so it is easy to map (and zip) stuff to each value
type Total a = (Fat a, Protein a, Sugar a, Starch a, Alcohol a)

baseAmount :: Amount Int
baseAmount = Amount (Grams 0) (Percent 0) (Calories 0)

baseTotal :: Total Int
baseTotal = (baseAmount, baseAmount, baseAmount, baseAmount, baseAmount)


sumPercentages :: Total Int -> Int
sumPercentages (fat, protein, sugar, starch, alcohol) = sum $ map getPercentage [fat, protein, sugar, starch, alcohol]

sumOtherCalories :: Total Int -> Int
sumOtherCalories (fat, protein, sugar, starch, alcohol) =
    sum $ map getTotalCalories [(fat, 9), (protein, 4), (sugar, 4), (starch, 4), (alcohol, 7)]

processResult :: Total Int -> Double
processResult t = bonusFatPercent + fromIntegral (fatPercent)
    where
        (fat, _, _, _, _) = t
        p = 100 - sumPercentages t
        totalCalories = 100 * fromIntegral (sumOtherCalories t) / fromIntegral p
        bonusFatPercent = (fromIntegral (getTotalCalories (fat, 9)) / totalCalories) * 100
        fatPercent = getPercentage fat

-- get all percentage -> 65 %
-- p = 100 - sum_percentages
-- s = sum all other calories
-- s -> p
-- x -> 100
-- total_calories = 100 * s / p -> gives percentage
-- bonus_fat = fat_calories (not percentage) / total_calories
-- total_fat = bonus_fat + (percentage fat)

processLines :: [String] -> Total Int
processLines = foldr sumTotals baseTotal . map processLine


sumAmounts :: Amount Int -> Amount Int -> Amount Int
sumAmounts (Amount (Grams g1) (Percent p1) (Calories c1)) (Amount (Grams g2) (Percent p2) (Calories c2)) =
    Amount (Grams $ g1 + g2) (Percent $ p1 + p2) (Calories $ c1 + c2)

sumTotals :: Total Int -> Total Int -> Total Int
sumTotals (f1, p1, s1, st1, a1) (f2, p2, s2, st2, a2) =
    (sumAmounts f1 f2, sumAmounts p1 p2, sumAmounts s1 s2, sumAmounts st1 st2, sumAmounts a1 a2)



processLine :: String -> Total Int
processLine s = (a1, a2, a3, a4, a5)
    where
        (a1, r1) = getValue s
        (a2, r2) = getValue r1
        (a3, r3) = getValue r2
        (a4, r4) = getValue r3
        (a5, _) = getValue r4


getValue :: String -> (Amount Int, String)
getValue s = case head rest of
        'g' -> (Amount (Grams (read fst :: Int)) (Percent 0) (Calories 0), tail rest)
        '%' -> (Amount (Grams 0) (Percent (read fst :: Int)) (Calories 0), tail rest)
        _ -> (Amount (Grams 0) (Percent 0) (Calories (read fst :: Int)), tail rest)
    where
        (fst, rest) = span isDigit s
