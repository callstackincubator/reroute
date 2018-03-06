module RouterConfig = {
  type route =
    | Admin
    | Home
    | NotFound;
  let routeFromUrl = (url: ReasonReact.Router.url) =>
    switch url.path {
    | ["admin"] => Admin
    | [] => Home
    | _ => NotFound
    };
  let routeToUrl = (route: route) =>
    switch route {
    | Admin => "/admin"
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
                 <Router.Link route=Home>
                   <li> (ReasonReact.stringToElement("Home")) </li>
                 </Router.Link>
                 <Router.Link route=Admin>
                   <li> (ReasonReact.stringToElement("Admin")) </li>
                 </Router.Link>
               </ul>
               (
                 switch currentRoute {
                 | RouterConfig.Admin => <Admin />
                 | RouterConfig.Home => <Home />
                 | RouterConfig.NotFound => <NotFound />
                 }
               )
             </div>
         )
    </Router.Container>
};