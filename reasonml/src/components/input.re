
let valueFromEvent evt :string => (evt |> ReactEventRe.Form.target |> ReactDOMRe.domElementToObj)##value;

type state = string;
let component = ReasonReact.statefulComponent "Input";
let make ::onSubmit _ => {
    ...component,
    initialState: fun () => "",
    render: fun {state: text, update} =>
    <input
        value=text
        _type=text
        placeholder="Write something to do"
        onChange=(update (fun evt _ => ReasonReact.Update (valueFromEvent evt)))
        onKeyDown=(
        update (
            fun evt {state: text} =>
            if (ReactEventRe.Keyboard.key evt == "Enter") {
                onSubmit text;
                ReasonReact.Update ""
            } else {
                ReasonReact.NoUpdate
            }
        )
        )
    />
};
