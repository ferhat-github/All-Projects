--Ferhat Kasim Koc
--I read and accept the submission rules and the extra rules specified in each question. This is my own work that is done by myself only.


data MultiTree = Empty | Node String Integer [MultiTree] deriving (Show, Eq, Ord)

--This function is the function that will create our MultiTree structure. It will add children to the relevant family node simply by using the "take" and "drop" functions.
treeMaking :: [(String, Integer)] -> [Integer] -> [MultiTree]
treeMaking [] _ = []
treeMaking _ [] = []
treeMaking ((name, worker) : xs) (n : ns) = Node name worker (take (fromIntegral n) (treeMaking xs ns)) : treeMaking (drop (fromIntegral n) xs) ns

--This function will only get the information of the root node. It will send the remaining information to the treeMaking function.
unitree :: [(String, Integer)] -> [Integer] -> MultiTree
unitree [] _ = Empty
unitree (x:xs) (y:ys) = Node (fst x) (snd x) (treeMaking xs ys)

--x is my sample MultiTree. I use it to call my other functions to see whether I coded them properly or not. In other words x will be used in sample run.
x = unitree [("Rectorate", 2), ("General Secretary", 6), ("Social Sciences", 2), ("Economics", 4), ("Political Science", 5), ("Education", 2), ("Pre School", 3), ("Foreign Languages", 4), ("Engineering", 4), ("Computer Engineering", 10), ("Mechanical Engineering", 5), ("Electrical Engineering", 6)] [3, 0, 3, 0, 0, 2, 0, 0, 3, 0, 0, 0]


-- ********************************************************************************************************************************************************************************

--This function will calculate the number of workers in the given node and the number of workers of that node's children and grandchildren, if any.
sectionsizeCounter :: MultiTree -> Integer
sectionsizeCounter Empty = 0
sectionsizeCounter (Node _ worker children) = worker + sum (map sectionsizeCounter children)  


sectionsize :: MultiTree -> String -> Integer
sectionsize Empty _ = 0
sectionsize (Node name worker children) sectionName = if name == sectionName then worker + sum (map sectionsizeCounter children)  --If there is a match in the name, it sums the number of workers in the node and the number of workers in their descendants (with the help of the sectionsizeCounter function).
                                                      else sum (map (\child -> sectionsize child sectionName) children)  --It continues to search for the desired name in its children and grandchildren if any.



-- ********************************************************************************************************************************************************************************


managingentity2 :: MultiTree -> String -> String -> String
managingentity2 (Node name _ children) target parentName = if name == target then parentName --If the entered Department matches the name of the current node, then parent will be returned.
                                                           else let parents = filter (/="") (map (\child -> managingentity2 child target name) children) in if null parents then "" else head parents --Filtering empty strings from the list of parent names obtained by recursively calling managingentity2 on each child node

--This function will be used to initiate the call to the parent department. To initialize it, it will send empty string "" as ParentName because root node does not have parent.
managingentity :: MultiTree -> String -> String
managingentity tree target = managingentity2 tree target ""



-- ********************************************************************************************************************************************************************************



--This function finds the parent of the given node
findingParent :: MultiTree -> String -> String -> String
findingParent Empty _ _ = ""
findingParent (Node name _ children) target currentParent = if name == target then currentParent else findingParentInside children target name



--This function iterates through the list of children recursively, using the first non-empty string which is found parent or continues if an empty string is returned.
findingParentInside :: [MultiTree] -> String -> String -> String
findingParentInside [] _ _ = ""
findingParentInside (x:xs) target parentName = let foundParent = findingParent x target parentName in if foundParent /= "" then foundParent else findingParentInside xs target parentName


--This function will build a path from section to the root
--It is called recursively and it updates the path each time the parent is found until no more parents are found which is indicated by an empty string
managelist2 :: MultiTree -> String -> [String] -> [String]
managelist2 _ "" path = path
managelist2 tree currentSection path = let parentName = findingParent tree currentSection "" in if parentName /= "" then managelist2 tree parentName (parentName : path) else path

--This function will be used to start managelist2 function with tree, target and an empty list parameters, then the returned value will be reversed to get desired order.
managelist :: MultiTree -> String -> [String]
managelist tree target = reverse (managelist2 tree target [])

