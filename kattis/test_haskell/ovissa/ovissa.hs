
main :: IO ()
main = do
    line <- getLine
    putStrLn $ show $ length line
