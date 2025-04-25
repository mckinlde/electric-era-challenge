#!/usr/bin/env bash
set -e

echo "📦 Setting up Electric Era challenge project..."

# Create project subfolders
mkdir -p test_data

# Create core source files
touch main.cpp
touch charger.hpp
touch charger.cpp

# Pull nlohmann/json single-header JSON library
curl -L -o json.hpp https://raw.githubusercontent.com/nlohmann/json/develop/single_include/nlohmann/json.hpp

# Clone official Electric Era GitLab repo into clearly named temp folder
echo "🌐 Cloning Electric Era public GitLab repo..."
git clone --depth=1 https://gitlab.com/electric-era-public/coding-challenge-charger-uptime.git test-data-upstream

# Copy official input/output test files
echo "📄 Copying input/output test files..."
cp test-data-upstream/input_1.txt test_data/input_1.txt
cp test-data-upstream/input_1_expected_stdout.txt test_data/expected_output_1.txt
cp test-data-upstream/input_2.txt test_data/input_2.txt
cp test-data-upstream/input_2_expected_stdout.txt test_data/expected_output_2.txt

# Clean up temporary clone
echo "🧹 Cleaning up temporary files..."
rm -rf test-data-upstream

# Add .gitignore entries to ignore build artifacts
echo "hello" >> .gitignore
echo "a.out" >> .gitignore
echo "build/" >> .gitignore

# Stage and commit new files
git add main.cpp charger.hpp charger.cpp json.hpp test_data/ .gitignore
git commit -m "chore: scaffold project structure and pull verified Electric Era test data"
git push

echo "✅ Setup complete!"
