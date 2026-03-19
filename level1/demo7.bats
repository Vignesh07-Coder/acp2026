#!/usr/bin/env bats

@test "basic execution with 2 students" {
    run ./demo <<< $'2\n1\nAlice Johnson\n92.5\n2\nBob Smith\n87.2\n'
    [ "$status" -eq 0 ]
    [[ "$output" == *"Original array"* ]]
    [[ "$output" == *"Data read from file"* ]]
} 
