module RouterConfig = {
  type route =
    | Admin
    | Home
    | NotFound;
  let routeFromUrl = (url: ReasonReactRouter.url) =>
    switch (url.path) {
    | ["admin"] => Admin
    | [] => Home
    | _ => NotFound
    };
  let routeToUrl = (route: route) =>
    switch (route) {
    | Admin => "/admin"
    | Home => "/"
    | NotFound => ""
    };
};

module Router = ReRoute.CreateRouter(RouterConfig);
open RouterConfig;
[@react.component]
let make = () => {
  <Router.Container>
    ...{(~currentRoute) =>
      <div>
        <ul>
          <h3> {React.string("Menu")} </h3>
          <Router.Link route=Home>
            <li> {React.string("Home")} </li>
          </Router.Link>
          <Router.Link route=Admin>
            <li> {React.string("Admin")} </li>
          </Router.Link>
        </ul>
        {switch (currentRoute) {
         | RouterConfig.Admin => <Admin />
         | RouterConfig.Home => <Home />
         | RouterConfig.NotFound => <NotFound />
         }}
      </div>
    }
  </Router.Container>;
};
