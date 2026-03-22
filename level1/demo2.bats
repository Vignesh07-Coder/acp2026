#!/usr/bin/env bats

# 1 Clear winner: Rectangle 1
@test "Rectangle 1 has the largest area" {
  run ./rectangle <<EOF
3
4
2
5
1
1
EOF
  [ "$status" -eq 0 ]
  [[ "$output" =~ "Rectangle 1 has the largest area = 12" ]]
}

# 2 Clear winner: Rectangle 2
@test "Rectangle 2 has the largest area" {
  run ./rectangle <<EOF
2
2
3
3
1
1
EOF
  [ "$status" -eq 0 ]
  [[ "$output" =~ "Rectangle 2 has the largest area = 9" ]]
}

# 3 Clear winner: Rectangle 3
@test "Rectangle 3 has the largest area" {
  run ./rectangle <<EOF
1
1
2
2
4
4
EOF
  [ "$status" -eq 0 ]
  [[ "$output" =~ "Rectangle 3 has the largest area = 16" ]]
}

# 4 Tie case: Rectangle 1 and 2 equal and largest
@test "Rectangle 1 and 2 tie for largest area" {
  run ./rectangle <<EOF
5
4
2
10
1
1
EOF
  [ "$status" -eq 0 ]
  [[ "$output" =~ "Rectangle 1 and Rectangle 2 have the largest equal area = 20" ]]
}

# 5 Invalid input: negative dimensions should be rejected
# Current program will still compute a negative area and print a winner.
@test "Reject negative dimensions" {
  run ./rectangle <<EOF
-3
4
2
2
1
1
EOF
  [ "$status" -ne 0 ]
  [[ "$output" =~ "Invalid" ]]
}

# 6 Invalid numeric edge case: NaN input should be rejected
# On many systems scanf("%f") accepts nan, and comparisons with NaN break the logic.
@test "Reject NaN input" {
  run ./rectangle <<EOF
nan
4
2
2
1
1
EOF
  [ "$status" -ne 0 ]
  [[ "$output" =~ "Invalid" ]]
}