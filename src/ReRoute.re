module type RouterConfig = {
  type route;
  let routeFromUrl: ReasonReact.Router.url => route;
  let routeToUrl: route => string;
};

module CreateRouter = (Config: RouterConfig) => {
  module Container = {
    type action =
      | ChangeRoute(Config.route);
    type state = Config.route;
    let component = ReasonReact.reducerComponent("Router");
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
    let component = ReasonReact.statelessComponent("Link");
    let make = (~route, children) => {
      ...component,
      render: _self => {
        let href = Config.routeToUrl(route);
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