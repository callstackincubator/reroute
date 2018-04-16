type windowLocationPathname = string;

[@bs.val] external pathname : windowLocationPathname = "window.location.pathname";

[@bs.send.pipe : string]
external split : string => array('a) = "";

let component = ReasonReact.statelessComponent("Book");

let make = _children => {
  ...component,
  render: _self => {
    let urlParam = (pathname |> split("/"));
    Js.log(urlParam[(Array.length(urlParam) - 1)]);
    <div>
      <h1> (ReasonReact.stringToElement("Book " ++ string_of_int(urlParam[(Array.length(urlParam) - 1)]))) </h1>
    </div>
  }
};
