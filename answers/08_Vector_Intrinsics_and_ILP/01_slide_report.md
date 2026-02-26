# Topic

Select one slide from the lecture, research more about the topic, and report on it.

## Selected topic

Page 3, "Fused-Multiply-Add (FMA)"

## Research

On of the slied contains Fused-Multiply-Add. As I didn't really get, why this is explizitly mentioned i reasearched about it.

### Why is it used?

Normally an Operation like this `a + (b * c)` would be rounded after the multiplication. After this the addition would be calculated and it would round again. This may be sufficient for most tasks, but it could be not precise enough and slow.

The solution to this is to have a seperate unit in the processor with an extra large 'memory' specifficly for this kind of operation. So the FMA-unit will calculate the product and the addition immediatly and only after that will it round the result to be able to get it into the 64-bit mask. 

This is faster and more precise and faster.

### example when its used: AI

One very recent usecase of this kind of operation is in AI. To be more specific in neural networks.
Here this kind of operation is the driving factor of the network.
The core operation inside such a network is show below:

$$y = f(\sum (w \cdot x) + b)$$

* $x$: The Input (e.g., an image pixel or part of a word). 
* $w$: The Weight. How important is this input?
* $b$: The Bias (a kind of base activation).