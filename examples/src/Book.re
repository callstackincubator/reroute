[@bs.val] [@bs.scope ("window", "location")] external pathname : string = "pathname";

[@bs.send.pipe : string]
external split : string => array('a) = "";

let component = ReasonReact.statelessComponent("Book");

let make = _children => {
  ...component,
  render: _self => {
    let urlParam = (pathname |> split("/"));
    let bookId = urlParam[(Array.length(urlParam) - 1)];
    <div>
      <h1> (ReasonReact.stringToElement("Book " ++ string_of_int(bookId))) </h1>
    </div>
  }
};
