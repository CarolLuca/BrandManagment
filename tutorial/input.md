Client event
```
Client
hh:mm:ss
ClientName
product(1) quantity(1)
product(2) quantity(2)
...
product(k) quantity(k)
-1 -1
StoreName
```

Manager event
```
Manager
hh:mm:ss
StoreName
```

StockUpdate event
```
StockUpdate
hh:mm:ss
product(1) quantity(1)
product(2) quantity(2)
...
product(k) quantity(k)
-1 -1
StoreName
```

Feedback event
```
Feedback
hh:mm:ss
ClientName
```

Closing command
```
END
```