let component = ReasonReact.statelessComponent("Home");

let make = _children => {
  ...component,
  render: _self =>
    <div>
      <h1> (ReasonReact.stringToElement("Home")) </h1>
      <p> (ReasonReact.stringToElement("Welcome to the home page!")) </p>
    </div>
};