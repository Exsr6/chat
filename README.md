# Little chat app

## What goes with what

- For the client, you need:
  - client.cpp (contains the main)
  - queue.h
  - receiver.cpp/h
  - util.h
- For the server, you need:
  - accepter.cpp/h
  - list.h
  - queue.h
  - receiver.cpp/h
  - server.cpp (contains the main)
  - util.h

Things can be factorised: most things can fit within a single class.

## Threads

We need a thread for the client, the server, the accepter and the receivers,
but they don't need to be in individual classes.

## Next steps

1. push the santorini code into its own git repo
2. make a branch networking
3. add the code from the chat blanks
4. make another commit and push it