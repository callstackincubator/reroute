module type RouterConfig = {
  type route;
  type param;
  let routeFromUrl: ReasonReact.Router.url => route;
  let routeToUrl: (route, param) => string;
};

module CreateRouter = (Config: RouterConfig) => {
  module Container = {
    type action =
      | ChangeRoute(Config.route);
    type state = Config.route;
    let component = ReasonReact.reducerComponent("CallstackRerouteRouter");
    let make = children => {
      ...component,
      initialState: () =>
        ReasonReact.Router.dangerouslyGetInitialUrl() |> Config.routeFromUrl,
      reducer: (action, _state) =>
        switch action {
        | ChangeRoute(route) => ReasonReact.Update(route)
        },
      subscriptions: self => [
        Sub(
          () =>
            ReasonReact.Router.watchUrl(url =>
              self.send(ChangeRoute(url |> Config.routeFromUrl))
            ),
          ReasonReact.Router.unwatchUrl
        )
      ],
      render: self => children(~currentRoute=self.state)
    };
  };
  module Link = {
    let component = ReasonReact.statelessComponent("CallstackRerouteLink");
    let make = (~route, ~param, children) => {
      ...component,
      render: _self => {
        let href = Config.routeToUrl(route, param);
        <a
          href
          onClick=(
            event => {
              ReactEventRe.Synthetic.preventDefault(event);
              ReasonReact.Router.push(href);
            }
          )>
          (ReasonReact.arrayToElement(children))
        </a>;
      }
    };
  };
};
