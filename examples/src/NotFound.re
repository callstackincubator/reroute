let component = ReasonReact.statelessComponent("NotFound");

let make = _children => {
  ...component,
  render: _self =>
    <div>
      <h1> (ReasonReact.stringToElement("We are sorry...")) </h1>
      <p>
        (
          ReasonReact.stringToElement(
            "Unfortunately we could not find the page you were looking for."
          )
        )
      </p>
      <p>
        (
          ReasonReact.stringToElement(
            "Use the above menu to navigate to other pages :)"
          )
        )
      </p>
    </div>
};