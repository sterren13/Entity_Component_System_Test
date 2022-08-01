# Funcites

# Data
- [[Block Layout]]
- pointer to buffer

# Block layout:
Entity 1 | Entity 2 | Entity 3
---------|----------|---------
Component 1 | Component 1 | Component 1
Component 2 | Component 2 | Component 2
Compoennt 3 | Component 3 | Component 3
Component 4 | Component 4 | Component 4
- Component moeten gesorteerd van klein naar groot om pending bit te verminderen om te voldoen aan de alignment.
- Memory moet doorlopend worden machen geen aprate arrays zijn.
- Moet een vaste grote hebben 16 kbits (kan groter maar dit hangt af van de CPU L1 cache)

## Memory layout
- copy data word memcpy instructie gedaan

-tx-
Adres | Data
------: | -----:
0 | Component 1
1 | ^^
2 | ^^
3 | Pending bit
4 | Component 1
5 | ^^
6 | ^^
7 | Pending bit
8 | Component 1
9 | ^^
10 | ^^
11 | Pending bit
12 | Component 2
13 | ^^
14 | Pending bit
15 | Pending bit
16 | Component 2
17 | ^^
18 | Pending bit
19 | Pending bit
20 | Component 2
21 | ^^
22 | Pending bit
23 | Pending bit
24 | Component 3
25 | Pending bit
26 | Component 3
27 | Pending bit
28 | Component 3
29 | Pending bit
...| rest






