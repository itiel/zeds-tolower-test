[//]: # (Author: Itiel Lopez - itiel@soyitiel.com)
[//]: # (Created: 18/08/2021)

# Zed's `tolower()` test

A program to compare the relative performance of `tolower()` alternative functions.

## Intro

This program is a recreation of a [similar program](https://gist.github.com/zed/370497) which itself is the result of the back and forth between [Oleg Razgulyaev *(oraz)*](https://stackoverflow.com/users/2153550/oleg-razgulyaev) and [Zed *(jfs)*](https://stackoverflow.com/users/4279/jfs) in [one of Oleg's answers](https://stackoverflow.com/a/2661917/2167133) to a question from stackoverflow about `tolower()` alternatives. 

Paraphrasing the [original author](https://gist.github.com/zed), the purpose of this program is to *compare the relative performance of `tolower()` alternative functions*.

The reason why I re-made the program was to see the inner workings of it and understand it better. Also, to add an in-program time counter instead of using Valgrind as the original program did. Sorry for that.

Here's a copy of [the original program](/zeds-test.c).

## How to test it

You can download the repo or clone it wtih `git` like this:

    $ git clone https://github.com/itiel/zeds-tolower-test.git

Then, from repo's root, run the test with `make` like this:
    
    $ make test-complete

which is equivalent to this:

    $ make test 1000000
    $ make test 10000000
    $ make test 50000000
    $ make test 100000000

Or, you can compile it with your prefered compiler:

    $ gcc -o tolower-test tolower-test.c 

and run the test like so:

    $ ./tolower-test 1000000
    $ ./tolower-test 10000000
    $ ./tolower-test 50000000
    $ ./tolower-test 100000000

## Results

I tested the program on different machines with different compilers and recorder the results.

Every test was done 3 times to get a more averaged result (needles to say my laptop crashed not long after because of memory issues, woops).

<table>
    <tr>
        <th rowspan="2">
            System/<br>
            Machine/<br>
            Compiler
        </th>
        <th rowspan="2">N. of tries</th>
        <th colspan="5">Time (secs) taken by function</th>
    </tr>
    <tr>
        <th><i>Oraz</i></th>
        <th><i>Oraz v2</i></th>
        <th><i>OpenBSD</i></th>
        <th><i>OpenBSD v2</i></th>
        <th><i>ctype</i></th>
    </tr>
    <tr>
        <td rowspan="4">
            WSL Ubuntu 20.04.2/<br>
            Intel i5-8265U 1.60GHz/<br>
            gcc 9.3.0 for Ubuntu
        </td>
        <td><i>1,000,000</i></td>
        <td>0.283</td>
        <td>0.290</td>
        <td>0.344</td>
        <td>0.288</td>
        <td>0.392</td>
    </tr>
    <tr>
        <td><i>10,000,000</i></td>
        <td>2.805</td>
        <td>2.869</td>
        <td>3.462</td>
        <td>2.430</td>
        <td>3.779</td>
    </tr>
    <tr>
        <td><i>50,000,000</i></td>
        <td>12.199</td>
        <td>12.874</td>
        <td>17.922</td>
        <td>13.418</td>
        <td>19.151</td>
    </tr>
    <tr>
        <td><i>100,000,000</i></td>
        <td>25.235</td>
        <td>28.473</td>
        <td>37.800</td>
        <td>26.304</td>
        <td>36.884</td>
    </tr><tr>
        <td rowspan="4">
            Microsoft Windows 10/<br>
            Intel i5-8265U 1.60GHz/<br>
            MinGW's gcc version 9.2.0
        </td>
        <td><i>1,000,000</i></td>
        <td>0.256</td>
        <td>0.262</td>
        <td>0.356</td>
        <td>0.247</td>
        <td>2.689</td>
    </tr>
    <tr>
        <td><i>10,000,000</i></td>
        <td>2.581</td>
        <td>2.526</td>
        <td>3.600</td>
        <td>2.572</td>
        <td>26.759</td>
    </tr>
    <tr>
        <td><i>50,000,000</i></td>
        <td>12.711</td>
        <td>13.46</td>
        <td>18.265</td>
        <td>12.891</td>
        <td>128.633</td>
    </tr>
    <tr>
        <td><i>100,000,000</i></td>
        <td>24.302</td>
        <td>24.814</td>
        <td>37.281</td>
        <td>24.203</td>
        <td>258.338</td>
    </tr>
</table>