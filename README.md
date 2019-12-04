# Equation-Parser-Interpreter

This is an file based interpriter for <a href = "https://github.com/YJDoc2/EquationParser">Equation Parser</a>.

## Basic Usage

#### Compiling

generate the runfile using makefile and make command (on linux), requires gcc and g++, with c++ std 14 support.

For manual compiling :

<ol>
<li>gcc -c cparser.c -lm ; which will give cparser.o </li>
<li>g++ -c main.cpp; which will give main.o </li>
<li>g++ -o eqparse cparser.o main.o; which will give eqparse</li>
</ol>

#### running

eqparse &lt;script_file&gt; [output_file]  (Without Brackets)

script file is any valid text file written with valid syntax.  
output file is optional.
If not given output will be given on standerd output - either console or redirected file if output redirection is done.
If given output will <b> Overwrite </b> the file.

## Syntax :

<ul>
<li>All Non-comment Lines should be less than 150 characters long in total.</li>
<li>Lines starting with ' // ' and empty lines will be ignored.</li>
<li>Contents of line starting with ' # ' will be copied as it is (except #) in the output.</li>
<li>All inbuilt commands, equations and variable assignments must be given on a line by themselves,i.e. Comments cannot start mid-way in a line.</li>
<li>Allowed inbuild commands Are : <b>showvars , vardump , varload , varclear.</b></li>
<li>to solve an equation, or for variable assignment, give the expression on the line by itself.</li>
<li>Assignment of variable can be done as :
<ol>
<li>$0 to $9 = expr ---for inbuilt variables</li>
<li>varname = expr ---for custom named variables.</li>
</ol>
</li>
<li>To find roots of a polynomial equation , use polysolve &lt;space&gt; expr</li>
<li>To solve system of linear equation with less than 9 variables:
<ul>
<li>First give linsolve &lt;space&gt; &lt;number of variables (n)&gt;</li>
<li>Then give the linear equations using variables x0 to x(n-1) on next consecutive lines.</li>
</ul>
</li>
</ul>

Also look at syntax of <a href ="https://github.com/YJDoc2/EquationParser/blob/master/Mark%20II/README.md"> Equation Parser Mk II </a> for general syntax.
