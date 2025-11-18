# testing and implementation

**Since the current state of the heap function builds from a given vector, we need to convert the map to a vectorform i think.**
- the only other thing i can think of is using the map directly
    - but this can be the next thing to try and make


## TODO:
- [ ] make a function that takes in the frequency table map, then creates a vector out of the pairs
    - i have kinda of done this? I think, but it relies on Node* being a public member atm
    - obviously not the most efficient way to go about this, but first step
- [ ] test out the heap creation
    - [ ] some unit test idk

## CHANGES TO CONSIDER
- changing the insert function from a Node* input to a char and freq input
    - this can keep the Node* to be a private/protected structure
    - keeps the Node* manipulation private/protected


