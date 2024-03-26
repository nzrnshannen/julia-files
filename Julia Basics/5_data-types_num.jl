# DATA TYPES: Number

#= 
NOTE: Ctrl + Shift + P and use "Julia: Start REPL" 
typeof() will work if you do Shift + Enter first on the lines of code above it
=#



#=
1 vs 1.0

1 is an integer
1.0 is a floating point number (with decimal point)
=#


# typeof() <- returns the data type of the value inside its ()
typeof(-3)
typeof(1.2)
#Int64 (64-bit integer)
#Float64 (64-bit floating point)


#=

Declaring a new variable: 
variable_name::data_type
variable_name::data_type = value

=#

example::Float32 = 1.2
typeof(example)

testNumber::Int64 = 5
typeof(testNumber)


####################################################
# Using equation inside typeof() is allowed

0.1 + 0.2 
1 / 3

typeof(1/3)
typeof(0.1 + 0.2)

# value//3 for Rational

1//3
typeof(1//3)

x = 1
y = 2
typeof(x + y)

# Rational value1 // value2 <-- fraction
1//3 + 1//7 
typeof(1//3 + 1//7)

#= Irrational 

1. pi 
2. round(value)
    -> round(value; digits = number_of_digits)
3. sqrt(value)
4. div(value1, value2)
    -> returns quotient
=#

# pi <- built-in in Julia
pi 
typeof(pi)

randomVal = 4.143985129
round(randomVal; digits = 3)

# Julia ignores underscores ( _ )
# Use this to make your values readable:
1000000 == 1_000_000

# Using sqrt()
sqrt(4)
sqrt(25)


#= 
From chapter on basic math

1. Int - Int = Int, 
    Int + Int = Int, 
    Int * Int = Int,
    BUT 
    Int / Int = Int or Float 
=#

# Using div()
div(4, 2)
div(10, 2)
div(2, 5)

# Trigger division symbol by using \div<tab>
# example:
# --> ÷
# 4 \div<tab> 2
4 ÷ 2
5 ÷ 2