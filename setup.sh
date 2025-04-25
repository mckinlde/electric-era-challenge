# Create project subfolders
mkdir -p test_data

# Create core source files
touch main.cpp
touch charger.hpp
touch charger.cpp

# Pull the nlohmann/json single-header library for JSON parsing
curl -L -o json.hpp https://raw.githubusercontent.com/nlohmann/json/develop/single_include/nlohmann/json.hpp

# Pull Electric Era official input/output files
# First test case
curl -L -o test_data/input.txt https://gitlab.com/electric-era-public/coding-challenge-charger-uptime/-/raw/main/input.txt
curl -L -o test_data/expected_output.txt https://gitlab.com/electric-era-public/coding-challenge-charger-uptime/-/raw/main/expected_output.txt

# Second test case
curl -L -o test_data/input_2.txt https://gitlab.com/electric-era-public/coding-challenge-charger-uptime/-/raw/main/input_2.txt
curl -L -o test_data/expected_output_2.txt https://gitlab.com/electric-era-public/coding-challenge-charger-uptime/-/raw/main/expected_output_2.txt

# Add .gitignore to ignore build artifacts
echo "hello" >> .gitignore
echo "a.out" >> .gitignore
echo "build/" >> .gitignore

# Stage everything into git
git add main.cpp charger.hpp charger.cpp json.hpp test_data/ .gitignore
git commit -m "chore: scaffold project structure and pull official Electric Era test data"
git push
