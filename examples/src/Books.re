let component = ReasonReact.statelessComponent("Books");

let make = _children => {
  ...component,
  render: _self =>
    <div>
      <h1> (ReasonReact.stringToElement("Books")) </h1>
      <ul>
        <li onClick=((_) => ReasonReact.Router.push("/book/1"))> (ReasonReact.stringToElement("Book 1")) </li>
        <li onClick=((_) => ReasonReact.Router.push("/book/2"))> (ReasonReact.stringToElement("Book 2")) </li>
        <li onClick=((_) => ReasonReact.Router.push("/book/3"))> (ReasonReact.stringToElement("Book 3")) </li>
      </ul>
    </div>
};
