# Doel:
- Houd component combinatie bij
- Component worden gestordeerd op grote

# Data:
- vector component

# Functies
## Create hash


````mermaid
graph TD
    A[Component Array]
    B[Start state]
    C[Component 1]
    D[Mix]
    A --> C
    B --> D
    C --> D
    E[State 1]
    D --> E
    F[Component 2]
    A --> F
    G[Mix]
    E --> G
    F --> G
    G --> H[State 2]
    J[Component 3]
    A --> J
    K[Mix]
    J --> K
    H --> K
    K --> L[State 3]
    A --> P[Component ...]
    L --> M[Mix ...]
    P --> M
    M --> U[State ...]
    U --> T[Hash out]
````

### Mix
- Input:
	- State = A
	- Component Hash = B
- Ouput
	- Hash = H
- Forume
	- $$ H = (A.B) XOR ((A << 3)+(B>>2))$$