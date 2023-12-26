#!/bin/bash

mkdir -p testsfiles

echo "var x = TRUE;" > testsfiles/test_var_declaration.txt
echo -e "var x = TRUE;\nx = FALSE;" > testsfiles/test_var_reassignment.txt
echo "var x = TRUE OR FALSE;" > testsfiles/test_var_expression.txt
echo -e "var x = TRUE;\nvar y = NOT x;" > testsfiles/test_var_usage.txt
echo -e "var x = TRUE;\nvar y = FALSE;\nvar z = x AND y;" > testsfiles/test_var_multiple.txt
