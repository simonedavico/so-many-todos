[%bs.raw {|require('./todoApp.css')|}];

open Types;

let se = ReasonReact.stringToElement;

type state = {todos: list todoItem};

let component = ReasonReact.statefulComponent "TodoApp";

/* can be dereferenced and mutated */
let lastId = ref 0;
let newItem text => {
  lastId := !lastId + 1;
  {id: !lastId, title: text, completed: false}
};

let toggleTodo todos id =>
  List.map (fun todo => todo.id === id ? {...todo, completed: not todo.completed} : todo) todos;

let addItem text {ReasonReact.state: state} =>
  ReasonReact.Update {...state, todos: [newItem text, ...state.todos]};

let deleteItem id _evt {ReasonReact.state: state} =>
  ReasonReact.Update {...state, todos: List.filter (fun t => t.id !== id) state.todos};

let make _ => {
  ...component,
  initialState: fun () => {todos: []},
  render: fun {state: {todos}, update} =>
    <div className="app">
      <div className="title"> (se "Reason ToDo List") <Input onSubmit=(update addItem) /> </div>
      <div className="items">
        (
          List.map
            (
              fun todo =>
                <TodoItem
                  key=(string_of_int todo.id)
                  todo
                  onToggle=(
                    update (
                      fun _ {state} =>
                        ReasonReact.Update {...state, todos: toggleTodo todos todo.id}
                    )
                  )
                  onDelete=(update (deleteItem todo.id))
                />
            )
            todos |> Array.of_list |> ReasonReact.arrayToElement
        )
        (
          List.length todos > 0 ?
            ReasonReact.nullElement : <div className="no-todos"> (se "No todos yet!") </div>
        )
      </div>
      <div className="footer">
        <div> (se ("Total todos: " ^ (List.length todos |> string_of_int))) </div>
        <div>
          {
            let numOfCompletedTodos: int =
              List.filter (fun todo => todo.completed) todos |> List.length;
            se ("Completed todos: " ^ string_of_int numOfCompletedTodos)
          }
        </div>
      </div>
    </div>
};