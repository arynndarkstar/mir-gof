# UML — Wave 2 Patterns (State, Memento, Null Object, Adapter, Facade, Builder)

## State

```mermaid
classDiagram
    direction LR
    class State~Context~ {
        <<interface>>
        +enter(Context&)
        +exit(Context&)
        +handle(Context&)
    }
    class StateContext~Context~ {
        -current_ State
        +change_state(...)
        +handle()
    }
    StateContext --> State : current
```

## Memento + Caretaker

```mermaid
classDiagram
    direction LR
    class Originator {
        +create_memento() Memento
        +restore(Memento)
    }
    class Memento {
        <<interface>>
    }
    class Caretaker {
        +push(Memento)
        +pop() Memento
    }
    Originator ..> Memento : creates
    Caretaker --> Memento : history
```

## Command + Memento (advanced)

```mermaid
classDiagram
    direction LR
    class MementoCommand {
        -originator_
        -before_ Memento
        -action_
        +execute()
        +undo()
    }
    MementoCommand --|> Command
    MementoCommand --> Originator
    MementoCommand --> Memento
```

## Null Object

```mermaid
classDiagram
    direction LR
    class Interface {
        <<interface>>
        +operation()
    }
    class RealObject {
        +operation()
    }
    class NullObject {
        +operation()  // no-op
    }
    RealObject --|> Interface
    NullObject --|> Interface
```

## Adapter (Object)

```mermaid
classDiagram
    direction LR
    class Target {
        <<interface>>
        +request()
    }
    class ObjectAdapter {
        -adaptee_
        +request()
    }
    class Adaptee {
        +specific_request()
    }
    ObjectAdapter --|> Target
    ObjectAdapter --> Adaptee : wraps
```

## Facade

```mermaid
classDiagram
    direction TB
    class Facade {
        +operation()
    }
    class SubsystemA
    class SubsystemB
    Facade --> SubsystemA
    Facade --> SubsystemB
```

## Builder

```mermaid
classDiagram
    direction LR
    class Builder~Product~ {
        <<interface>>
        +reset()
        +build_part_a()
        +build_part_b()
        +get_result() Product
    }
    class Director {
        +construct(Builder)
    }
    Director --> Builder : uses
```
