let component = ReasonReact.statelessComponent("Admin");

let make = _children => {
  ...component,
  render: _self =>
    <div>
      <h1> (ReasonReact.stringToElement("Admin")) </h1>
      <p> (ReasonReact.stringToElement("This is an admin page")) </p>
    </div>
};