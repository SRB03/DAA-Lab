## Week 01 - Lab Exercises and Plotting Guide

### Lab Questions Overview
This week's lab consists of the following six exercises:
## Lab Questions Summary

| Question | Topic | Task Summary |
| :--- | :--- | :--- |
| **1** | Order of Growth | Place given mathematical functions in a list by increasing order of growth for sufficiently large values of $n$. |
| **2** | Coin Simulation | Show the probability of getting a HEAD by tossing a fair coin is about 0.5, and extend the simulation to compare fair vs biased coins. |
| **3** | Bubble Sort Performance | Implement two versions of bubble sort for randomized data (one terminating early, one always completing the $(n-1)^{th}$ pass) and analyze their efficiency. 
| **4** | Towers of Hanoi (ToH) | Simulate the solution for $n$-discs, plot the total number of moves required, and draw a conclusion from the obtained plot. |
| **5** | Partition Point | Find the exact point of transition in an array containing a sequence of 0s followed by a sequence of 1s. |
| **6** | Element Uniqueness | Check for duplicates within a set of $n$ random numbers and provide a conclusion about the method for a sufficiently large value of $n$. |

### Prerequisites
To run these C programs, you must have a C compiler (such as `gcc`) installed on your system.
* **Linux:** Can be installed via `sudo dnf install build-essential`. (depends on ur particular distro's package manager (`dnf`, `apt`))
* **macOS:** Install Apple's Command Line Tools via terminal using `xcode-select --install`.
* **Windows:** Install MinGW-w64.

## Plotting with Gnuplot
Several questions in this lab require visualizing algorithm performance and simulation results (such as the Bubble Sort comparisons and Towers of Hanoi moves). The `.png` plot files included in this repository were generated using **Gnuplot**, a versatile command-line driven graphing utility. 

If you wish to run the plotting scripts to recreate or modify these graphs yourself, you will need to install Gnuplot on your system.

### How to Install Gnuplot

**Linux (Fedora, Ubuntu)**
Open your terminal and as per your distro's package manager (`dnf`, `apt`):
```bash
sudo dnf install gnuplot
```
**macOS**
The most straightforward method on macOS is via Homebrew. Open your terminal and run:
```Bash
brew install gnuplot
```
**Windows**
You can quickly install Gnuplot using the Winget package manager via Command Prompt or PowerShell:
```DOS
winget install Gnuplot.Gnuplot
```