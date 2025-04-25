#!/usr/bin/env bash
set -e

echo "🛠 Building submission..."
g++ -std=c++17 -O2 main.cpp -o hello

echo "🚀 Running test 1 (input.txt)..."
./hello < test_data/input.txt > test_data/output_test1.txt

echo "🧪 Comparing against expected_output.txt..."
if diff -u test_data/expected_output.txt test_data/output_test1.txt; then
  echo "✅ Test 1 Passed!"
else
  echo "❌ Test 1 FAILED!"
fi

echo ""
echo "🚀 Running test 2 (input_2.txt)..."
./hello < test_data/input_2.txt > test_data/output_test2.txt

echo "🧪 Comparing against expected_output_2.txt..."
if diff -u test_data/expected_output_2.txt test_data/output_test2.txt; then
  echo "✅ Test 2 Passed!"
else
  echo "❌ Test 2 FAILED!"
fi
