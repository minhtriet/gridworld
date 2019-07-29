## Todo
Add code of stuffs, before and after


## To run
### Compile
`./compile.sh`
### Run with different files
`./a.out [input.txt | input2.txt | ... ]`

## About this repo
Implementation of gridworld problem, Artificial Intelligence: A Modern Approach v3, Chapter 17, Exercise 11.

Reiforcement realing


## Motivation
The motivation of this is two fold:

1. According to Suttons’s book, there are two classes of RL, one that states and action space can be effectively stored on a table. Another case is that the states 

While the latter case generates more hype, I find the former case good for education purpose. Not the magical blackbox of Neural Network, mostly non bullshit number.

2. After having my take of some data company and Internet blogs, I realize what is done anyway is throwing in data and a generic neural network (NN), I feel like it is  more beneficial to readers to either implement a paper (and do debugging techniques like gradient check before tuning hyperparameters) 
or
2. Do some classical tabular RL method


## Prerequiste
Know about basic concept of state, … in RL, I summarise them at the appendix


## Technical details
The premise of RL is around Markov decision process, 

We use BFS with Bellman equation for value update
### Index matters
 When accessing a 2D array, the order of index often looks like
```
for i in range(rows):
    for j in range(columns):
        print(matrix[i][j])
```
However, common math convetion requies `x` coordinate (corresponds to `width`) comes before `y`, which conflicts with the `(height, width)` convention above. There also those kind of inconsistent, even in mature library (Compare https://docs.opencv.org/4.0.0/d3/d63/classcv_1_1Mat.html#a2ec3402f7d165ca34c7fd6e8498a62ca with https://docs.opencv.org/4.0.0/d3/d63/classcv_1_1Mat.html#a75a97b1e4e55f380c172af58048a7cde). 

If `width != height`, in a language like C++, instead of throwing an exception, a random number would be returned, which would lead to unpredictable result.

Solving this may requires altering one's convention
```
for i in range(width):
    for j in range(height):
        print(states[j][i])  # note the change of index here
```

It would be sensible to make one's own convention and to follow it to make it a habit.

### Non-obvious edge cases
It is common to use an initial value for value and then updated it when a better policy is found. I would use a simple tuple `(x, y)` to indicate the policy



A naive initialization looks like

```
for i in range(width):
    for j in range(height):
        policy = (0, 0)
```

No direction, negative value

Now states would never get updated because the state would be 0, better than moving in any direction 
However, if run, result would be


Book of Sutton called this in 2.6. Overall, it is highly depending on your initial value. As @Programmer says, hours of minutes of reading the manual


## Initialize condition
If one looks at the update condition


He might be tempted to write this

if (result > best_result) {
    best_result = result;
    best_direction = direction;
}

But in reality, code is a problem
