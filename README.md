# SIR Model

Last year I tried to learn about epidemiological models, starting with Susceptible Infectious Recovered (SIR) [1](https://en.wikipedia.org/wiki/Compartmental_models_in_epidemiology). I tried to solve the equations using the Euler Method, but it did not went well. The Euler Method don't keep the population constant, this can be seen "sir_euler_total_pop.png". So I used the GSL to solve de coupled equations, the graphs can be seen in the "sir_rk45_curves.png". 

Later I did an dynamical code, where the particles move in a matrix. If a susceptible became neighbour with an infected it turns to infected. After some time the infected become recovered. There is some problem with this code, that I will work it on some day, the particles can move in diagonal. In a Random Walker model they can only move in vertical or horizontal. This can mess up my results. The curves of this dynamical simulation has some resemblance of the continous simulations.

In all my models the particles/persons cannot die. 

All comments are in portugese.
