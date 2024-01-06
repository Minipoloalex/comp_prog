import Text.Read (read)
import Data.List (sort)
{-
custom order light strips in lengths of whole meters, which cost x SEK per meter
average cost for each light strip ordered is at most y SEK per light strip.
-}
main :: IO ()
main = do
    num_str <- getLine
    let n = read num_str :: Int         -- number of ...
    cost_str <- getLine
    let x = read cost_str :: Int        -- cost per meter
    max_cost_str <- getLine
    let y = read max_cost_str :: Int    -- highest avg cost
    integers_str <- getLine
    let integers = map (\x -> read x :: Int) $ words integers_str
    solve 0 0 x y $ sort integers

solve :: Int -> Int -> Int -> Int -> [Int] -> IO ()
solve total_cost total_lights _ _ [] = print total_lights
solve total_cost total_lights x y (l:lights)
    | fromIntegral (total_cost + l * x) / fromIntegral (total_lights + 1) > fromIntegral y   = print total_lights
    | otherwise = solve (total_cost + l * x) (total_lights + 1) x y lights
