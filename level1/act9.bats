##!/usr/bin/env bats

@test "Test 1: Handle 0 employees" {
run ./payroll <<EOF
0
EOF

[ "$status" -eq 0 ]
[[ "$output" =~ "TOTAL MONTHLY PAYROLL: \$0.00" ]]

echo "Test 1 passed"
}

@test "Test 2: Single employee" {
run ./payroll <<EOF
1
101
Alice
5000.50
EOF

[ "$status" -eq 0 ]
[[ "$output" =~ "TOTAL MONTHLY PAYROLL: \$5000.50" ]]

echo "Test 2 passed"
}

@test "Test 3: Maximum capacity" {

input=$(printf "50\n"; for i in {1..50}; do printf "%d\nUser%d\n1.00\n" "$i" "$i"; done)

run ./payroll <<< "$input"

[ "$status" -eq 0 ]
[[ "$output" =~ "TOTAL MONTHLY PAYROLL: \$50.00" ]]

echo "Test 3 passed"
}

@test "Test 4: Name with spaces" {

run ./payroll <<EOF
1
102
Elon Musk
1000.00
EOF

[ "$status" -eq 0 ]
[[ "$output" =~ "TOTAL MONTHLY PAYROLL: \$1000.00" ]]

echo "Test 4 passed"
}

@test "Test 5: High precision decimals" {

run ./payroll <<EOF
2
201
A
10.12345
202
B
20.12345
EOF

[ "$status" -eq 0 ]
[[ "$output" =~ "TOTAL MONTHLY PAYROLL: \$30.2" ]]

echo "Test 5 passed"
}

@test "Test 6: Large salaries" {

run ./payroll <<EOF
2
301
CEO
10000000.00
302
CTO
10000000.00
EOF

[ "$status" -eq 0 ]
[[ "$output" =~ "20000000.00" ]]

echo "Test 6 passed"
}

@test "Test 7: Negative salary" {

run ./payroll <<EOF
2
401
Debit
-500.00
402
Credit
1000.00
EOF

[ "$status" -eq 0 ]
[[ "$output" =~ "TOTAL MONTHLY PAYROLL: \$500.00" ]]

echo "Test 7 passed"
}

@test "Test 8: Long name buffer" {

long_name=$(printf 'a%.0s' {1..60})

run ./payroll <<EOF
1
501
$long_name
100.00
EOF

[ "$status" -eq 0 ]
[[ "$output" =~ "TOTAL MONTHLY PAYROLL: \$100.00" ]]

echo "Test 8 passed"
}

@test "Test 9: Special characters name" {

run ./payroll <<EOF
1
601
O'Connor-Smith
2500.00
EOF

[ "$status" -eq 0 ]
[[ "$output" =~ "TOTAL MONTHLY PAYROLL: \$2500.00" ]]

echo "Test 9 passed"
}

@test "Test 10: File persistence" {

rm -f payroll.txt

run ./payroll <<EOF
1
701
PersistUser
123.45
EOF

[ -f "payroll.txt" ]
grep -q "PersistUser" payroll.txt

echo "Test 10 passed"
}