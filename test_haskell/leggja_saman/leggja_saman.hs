import Text.Read (read)


main :: IO ()
main = do
    x <- getLine
    y <- getLine
    let x' = read x :: Int
    let y' = read y :: Int
    putStrLn $ show (x' + y')
