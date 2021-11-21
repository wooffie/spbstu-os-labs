#!/bin/bash

export VAR1=8
export VAR2=2
echo -n "$VAR1 + $VAR2 = "
let val1=VAR1+VAR2
echo "$val1 - addition of numbers"
echo ""
echo -n "$VAR1 - $VAR2 = "
let val2=VAR1-VAR2
echo "$val2 - subtract of numbers"
echo ""
echo -n "$VAR1 * $VAR2 = "
let val3=VAR1*VAR2
echo "$val3 - multiplication of numbers"
echo ""
echo -n "$VAR1 / $VAR2 = "
let val4=VAR1/VAR2
echo "$val4 - division of numbers"
echo ""
echo -n "$VAR1 % $VAR2 = "
let val5=VAR1%VAR2
echo "$val5 - remainder of division of numbers"
echo ""
echo -n "$VAR1 ** $VAR2 = "
let val6=VAR1**VAR2
echo "$val6 - raising $VAR1 to the power of $VAR2"
echo ""
