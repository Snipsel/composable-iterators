# Composable Iterators

## `range`
- `range(end)`
- `range(begin, end)`
- `range(begin, end, step)`

| Example            | Result          |
| ------------------ | --------------- |
| `range(4)`         | [0, 1, 2, 3]    |
| `range(-4)`        | [0, -1, -2, -3] |
| `range(2, 6)`      | [2, 3, 4, 5]    |
| `range(2, -2)`     | [2, 1, 0, -1]   |
| `range(5, -10, 4)` | [5, 1, -3, -7]  |
| `range(2, 10, 2)`  | [2, 4, 6, 8]    |

## `enumerate`
- `it | enumerate()`

Example:
```c++
for( auto&& [i,v] : range(5, -10, 4) | enumerate() )
    printf("%ld: %ld\n", i, v);
```
output:
```
0: 5
1: 1
2: -3
3: -7
```

## `filter`
- `it | filter( func )`

Example:
```c++
for( auto const i : range(5) | filter([](auto x){return x!=3;}) )
    printf("%ld\n", i);
```
output:
```
0
1
2
4
```

## `fold`
- `it | fold( init, func)`

Example:
```c++
printf("sum: %ld\n", range(5) | fold(0L, [](auto acc, auto b){return a+b;}) )
```
output:
```
sum: 10
```

