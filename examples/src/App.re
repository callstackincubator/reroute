module RouterConfig = {
  type param = string;
  type route =
    | Admin
    | Home
    | Books
    | Book
    | NotFound;
  let routeFromUrl = (url: ReasonReact.Router.url) =>
    switch url.path {
    | ["admin"] => Admin
    | ["books"] => Books
    | ["book", param] => Book
    | [] => Home
    | _ => NotFound
    };
  let routeToUrl = (route: route, param) =>
    switch route {
    | Admin => "/admin"
    | Books => "/books"
    | Book => "/book/" ++ param
    | Home => "/"
    | NotFound => ""
    };
};

module Router = ReRoute.CreateRouter(RouterConfig);

let component = ReasonReact.statelessComponent("App");

let make = _children => {
  ...component,
  render: _self =>
    <Router.Container>
      ...(
           (~currentRoute) =>
             <div>
               <ul>
                 <h3> (ReasonReact.stringToElement("Menu")) </h3>
                 <Router.Link param="" route=Home>
                   <li> (ReasonReact.stringToElement("Home")) </li>
                 </Router.Link>
                 <Router.Link param="" route=Admin>
                   <li> (ReasonReact.stringToElement("Admin")) </li>
                 </Router.Link>
                 <Router.Link param="" route=Books>
                   <li> (ReasonReact.stringToElement("Books")) </li>
                 </Router.Link>
               </ul>
               (
                 switch currentRoute {
                 | RouterConfig.Admin => <Admin />
                 | RouterConfig.Home => <Home />
                 | RouterConfig.Books => <Books />
                 | RouterConfig.Book => <Book />
                 | RouterConfig.NotFound => <NotFound />
                 }
               )
             </div>
         )
    </Router.Container>
};
