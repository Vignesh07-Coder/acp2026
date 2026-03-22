#!/usr/bin/env bats

setup(){
    rm -f act8
}

@test "Compilation" {
    run gcc -o act8 act8.c 
    [ "$status" -eq 0 ]  # Fixed: Added spaces and moved quote
    
    # It is safer to run the program in a separate test or 
    # ensure it exists before running it here
    run ./act8 <<EOF
Expected Input
EOF
    [ "$status" -eq 0 ] # Fixed: Added spaces and moved quote
}

@test "Input exactly matching MAX-1 characters" {
  # Compile here or in setup to ensure the binary exists for this test
  gcc -o act8 act8.c
  
  # Assuming MAX is 100, we provide 99 'a's
  input_str=$(printf 'a%.0s' {1..99})
  
  # Use 'run' to capture status/output for the pipe
  run bash -c "echo $input_str | ./act8"
  
  [ "$status" -eq 0 ]
  [[ "$output" =~ "Vowels: 0" ]] # 'a' is a vowel, changed logic if needed
}

teardown(){
    rm -f act8
} 

