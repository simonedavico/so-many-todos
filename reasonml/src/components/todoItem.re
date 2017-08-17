open Types;
let se = ReasonReact.stringToElement;

let component = ReasonReact.statelessComponent "TodoItem";
let make ::todo onToggle::onClick ::onDelete _children => {
    ...component,
    render: fun _ =>
    <div className="item">
        <div className=("item-content" ^ (todo.completed ? " completed" : "")) onClick>
        <input _type="checkbox" checked=(Js.Boolean.to_js_boolean todo.completed) />
        (se todo.title)
        </div>
        <i className="fa fa-times" onClick=onDelete />
    </div>
};
  