#!/usr/bin/env bats

print_success() {
  echo "✨ Test $1 passed"
}

@test "Test 1: Single modern car" {
  run ./prob4 <<EOF
1
Tesla
1
2023
50000
EOF

  [ "$status" -eq 0 ]
  [[ "$output" =~ "Tesla" ]]

  print_success 1
}

@test "Test 2: No modern cars" {
  run ./prob4 <<EOF
1
BMW
1
2020
30000
EOF

  [ "$status" -eq 0 ]
  [[ "$output" =~ "None" ]]

  print_success 2
}

@test "Test 3: Multiple cars mixed" {
  run ./prob4 <<EOF
3
Audi
1
2023
40000
BMW
2
2020
30000
Tesla
3
2024
60000
EOF

  [ "$status" -eq 0 ]
  [[ "$output" =~ "Audi" ]]
  [[ "$output" =~ "Tesla" ]]

  print_success 3
}

@test "Test 4: Invalid n then valid n" {
  run ./prob4 <<EOF
-1
abc
2
Tesla
1
2023
50000
BMW
2
2021
30000
EOF

  [ "$status" -eq 0 ]

  print_success 4
}

@test "Test 5: Invalid price recovery" {
  run ./prob4 <<EOF
1
Tesla
1
2023
abc
50000
EOF

  [ "$status" -eq 0 ]

  print_success 5
}

@test "Test 6: Max cars limit enforced" {
  run ./prob4 <<EOF
20
Tesla
1
2023
50000
EOF

  [ "$status" -eq 0 ]

  print_success 6
}

@test "Test 7: Long model name handled" {
  run ./prob4 <<EOF
1
SuperLongCarNameThatExceedsBufferSizeLimitTestingSafetyMechanism
1
2023
50000
EOF

  [ "$status" -eq 0 ]

  print_success 7
}

@test "Test 8: Invalid car_id recovery" {
  run ./prob4 <<EOF
1
Tesla
abc
1
2023
50000
EOF

  [ "$status" -eq 0 ]

  print_success 8
}

@test "Test 9: Invalid manufacture year recovery" {
  run ./prob4 <<EOF
1
Tesla
1
abcd
2023
50000
EOF

  [ "$status" -eq 0 ]

  print_success 9
}

@test "Test 10: Stress with mixed invalid inputs" {
  run ./prob4 <<EOF
xyz
-5
2
Tesla
abc
1
abcd
2023
abc
50000
BMW
2
2024
40000
EOF

  [ "$status" -eq 0 ]

  print_success 10
}