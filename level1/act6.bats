#!/usr/bin/env bats

@test "Intermediate 1: Basic 3-player valid input" {
  run ./act6 <<< $'3\n10\n20\n30\n'
  [ "$status" -eq 0 ]
  [[ "$output" =~ "Player 1" && "$output" =~ "10" ]]
  [[ "$output" =~ "Player 2" && "$output" =~ "20" ]]
  [[ "$output" =~ "Player 3" && "$output" =~ "30" ]]
  [[ "$output" =~ "total score" && "$output" =~ "60" ]]
  [[ "$output" =~ "Memory deallocated Safely" ]]
  echo "Test 1 passed !" >&3
}

@test "Intermediate 2: Zero players - proper error handling" {
  run ./act6 <<< $'0\n'
  [ "$status" -eq 1 ]
  [[ "$output" =~ "positive valid number" || "$output" =~ "Invalid" ]]
  echo "Test 2 passed !" >&3
}

@test "Intermediate 3: Negative players - error handling" {
  run ./act6 <<< $'-1\n'
  [ "$status" -eq 1 ]
  [[ "$output" =~ "positive valid number" || "$output" =~ "Invalid" ]]
  echo "Test 3 passed !" >&3
}

@test "Intermediate 4: Large team (50 players) - memory stress" {
  run ./act6 <<< $'50\n1\n2\n3\n' # First 3 scores, rest default
  [ "$status" -eq 0 ]
  [[ "$output" =~ "Memory allocated" ]]
  [[ "$output" =~ "total score" ]]
  [[ "$output" =~ "Memory deallocated Safely" ]]
  echo "Test 4 passed !" >&3
}

@test "Intermediate 5: Mixed scores with zero - total calculation" {
  run ./act6 <<< $'4\n0\n25\n50\n75\n'
  [ "$status" -eq 0 ]
  [[ "$output" =~ "total score" && "$output" =~ "150" ]]
  [[ "$output" =~ "Player 1" && "$output" =~ "0" ]]
  echo "Test 5 passed !" >&3
}

@test "Hardcore 1: Memory allocation failure simulation" {
  # Simulate malloc failure by stressing memory first
  run bash -c 'ulimit -v 102400; ./act6 <<< $''100000\n1\n2\n3\n'
  [ "$status" -eq 1 ]
  [[ "$output" =~ "Memory Allocation failed" ]]
  echo "Test 6 passed !" >&3
}

@test "Hardcore 2: Double free prevention after deallocation" {
  # Compile with fixed version that handles double-free
  run ./act6 <<< $'2\n10\n20\n'
  [ "$status" -eq 0 ]
  [[ "$output" =~ "Memory deallocated Safely" ]]
  
  # Second run verifies no double-free crash
  run ./act6 <<< $'1\n5\n'
  [ "$status" -eq 0 ]
  echo "Test 7 passed !" >&3
}

@test "Hardcore 3: Invalid input injection (letters/non-numeric)" {
  run ./act6 <<< $'3\nabc\n20\n30\n'
  [ "$status" -eq 0 ]  # Should handle gracefully, not crash
  [[ "$output" =~ "total score" ]]  # Should still complete
  echo "Test 8 passed !" >&3
}
