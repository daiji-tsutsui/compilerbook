#!/bin/bash
assert() {
    expected="$1"
    input="$2"

    result=$(execute_9cc "$input")

    if [ "$result" = "$expected" ]; then
        echo "$input => $result"
    else
        echo "$input => $expected expected, but got $result"
        exit 1
    fi
}

execute_9cc() {
    ./9cc "$1" > tmp.s
    cc tmp.s -o tmp
    ./tmp
    echo "$?"
}

assert 0 0
assert 42 42
assert 21 5+20-4
assert 111 307-245-19+68
assert 41 " 12 + 34 - 5 "

echo OK
