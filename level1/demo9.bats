#!/usr/bin/env bats

setup() {
  rm -f students.txt
}

run_with_input() {
  local input="$1"
  run ./demo9 <<< "$input"
}

# -------------------------
# 5 INTERMEDIATE CASES
# -------------------------

@test "Intermediate 1: n = 101 (overflow students1)" {
  input="101"
  for i in $(seq 1 101); do
    input+=$'\n'"$i student$i 90.0"
  done

  run_with_input "$input"
  [ "$status" -ne 0 ]
}

@test "Intermediate 2: n = 150 (larger overflow)" {
  input="150"
  for i in $(seq 1 150); do
    input+=$'\n'"$i name$i 75.5"
  done

  run_with_input "$input"
  [ "$status" -ne 0 ]
}

@test "Intermediate 3: file read overflow (120 records)" {
  rm -f students.txt
  for i in $(seq 1 120); do
    echo "$i name$i 88.8" >> students.txt
  done

  run ./demo9 <<< $'1\n1 alpha\n10'
  [ "$status" -ne 0 ]
}

@test "Intermediate 4: tampered file with 130 records" {
  input="100"
  for i in $(seq 1 100); do
    input+=$'\n'"$i s$i 60.0"
  done

  run ./demo9 <<< "$input"

  : > students.txt
  for i in $(seq 1 130); do
    echo "$i hacked$i 99.9" >> students.txt
  done

  run ./demo9 <<< $'1\n1 a\n1'
  [ "$status" -ne 0 ]
}

@test "Intermediate 5: invalid n (non-numeric)" {
  run ./demo9 <<< $'abc'
  [ "$status" -ne 0 ]
}

# -------------------------
# 10 HARD CASES
# -------------------------

@test "Hard 1: n = 1000" {
  input="1000"
  for i in $(seq 1 1000); do
    input+=$'\n'"$i a 1.0"
  done

  run_with_input "$input"
  [ "$status" -ne 0 ]
}

@test "Hard 2: n = INT_MAX" {
  run ./demo9 <<< $'2147483647'
  [ "$status" -ne 0 ]
}

@test "Hard 3: huge n with insufficient input" {
  run timeout 2 ./demo9 <<< $'999999999\n1 a 1.0\n2 b 2.0'
  [ "$status" -ne 0 ]
}

@test "Hard 4: file with 500 records" {
  rm -f students.txt
  for i in $(seq 1 500); do
    echo "$i name$i 77.7" >> students.txt
  done

  run ./demo9 <<< $'1\n1 a\n1'
  [ "$status" -ne 0 ]
}

@test "Hard 5: file with 1000 records" {
  rm -f students.txt
  for i in $(seq 1 1000); do
    echo "$i name$i 55.5" >> students.txt
  done

  run ./demo9 <<< $'1\n1 a\n1'
  [ "$status" -ne 0 ]
}

@test "Hard 6: alternating corrupt lines" {
  rm -f students.txt
  for i in $(seq 1 200); do
    echo "$i good$i 66.6" >> students.txt
    echo "BADLINE_$i" >> students.txt
  done

  run ./demo9 <<< $'1\n1 a\n1'
  [ "$status" -ne 0 ]
}

@test "Hard 7: extremely long numeric tokens" {
  rm -f students.txt
  printf "1 %0500d 99.9\n" 0 > students.txt
  printf "2 %0500d 88.8\n" 1 >> students.txt
  printf "3 %0500d 77.7\n" 2 >> students.txt

  run ./demo9 <<< $'1\n1 a\n1'
  [ "$status" -ne 0 ]
}

@test "Hard 8: negative n" {
  run ./demo9 <<< $'-999999999\n1 a 1.0\n2 b 2.0'
  [ "$status" -ne 0 ]
}

@test "Hard 9: zero n with poisoned file" {
  rm -f students.txt
  for i in $(seq 1 250); do
    echo "$i poison$i 91.1" >> students.txt
  done

  run ./demo9 <<< $'0'
  [ "$status" -ne 0 ]
}

@test "Hard 10: repeated overflow readback" {
  rm -f students.txt
  for i in $(seq 1 300); do
    echo "$i x$i 10.0" >> students.txt
  done

  run ./demo9 <<< $'2\n1 a 1.0\n2 b 2.0'
  [ "$status" -ne 0 ]
}