[//]: # (Author: Itiel Lopez - itiel@soyitiel.com)
[//]: # (Created: 18/08/2021)

# Zed's `tolower()` test

A program to compare the relative performance of `tolower()` alternative functions.

## Intro

This program is a recreation of a [similar program](https://gist.github.com/zed/370497) which itself is the result of the back and forth between [Oleg Razgulyaev *(oraz)*](https://stackoverflow.com/users/2153550/oleg-razgulyaev) and [Zed *(jfs)*](https://stackoverflow.com/users/4279/jfs) in [one of Oleg's answers](https://stackoverflow.com/a/2661917/2167133) to a question from stackoverflow about `tolower()` alternatives. 

Paraphrasing the [original author](https://gist.github.com/zed), the purpose of this program is to *compare the relative performance of `tolower()` alternative functions*.

The reason why I re-made the program was to see the inner workings of it and understand it better. Also, to add an in-program time counter instead of using Valgrind as the original program did. Sorry for that.

## The results

<table>
    <tr>
        <th rowspan="2">Machine/<br>Compiler</td>
        <th rowspan="2">N. of tries</td>
        <th colspan="4">Time (secs) taken by function</td>
    </tr>
    <tr>
        <th><i>Oraz</i></th>
        <th><i>Oraz v2</i></th>
        <th><i>ctype</i></th>
        <th><i>OpenBSD</i></th>
    </tr>
    <tr>
        <td rowspan="3">Machine 1</td>
        <td style="text-align: center">100,000</td>
        <td>10.0000</td>
        <td>10.0000</td>
        <td>10.0000</td>
        <td>10.0000</td>
    </tr>
    <tr>
        <td>100,000</td>
        <td>10.0000</td>
        <td>10.0000</td>
        <td>10.0000</td>
        <td>10.0000</td>
    </tr>
    <tr>
        <td>100,000</td>
        <td>10.0000</td>
        <td>10.0000</td>
        <td>10.0000</td>
        <td>10.0000</td>
    </tr>
</table>