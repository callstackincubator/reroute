module type RouterConfig = {
  type route;
  let routeFromUrl: ReasonReactRouter.url => route;
  let routeToUrl: route => string;
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
        ReasonReactRouter.dangerouslyGetInitialUrl() |> Config.routeFromUrl,
      reducer: (action, _state) =>
        switch (action) {
        | ChangeRoute(route) => ReasonReact.Update(route)
        },
      didMount: self => {
        let watcherID =
          ReasonReactRouter.watchUrl(url =>
            self.send(ChangeRoute(url |> Config.routeFromUrl))
          );
        self.onUnmount(() => ReasonReactRouter.unwatchUrl(watcherID));
      },
      render: self => children(~currentRoute=self.state),
    };
  };
  module Link = {
    let component = ReasonReact.statelessComponent("CallstackRerouteLink");
    let make = (~route, children) => {
      ...component,
      render: _self => {
        let href = Config.routeToUrl(route);
        <a
          href
          onClick=(
            event => {
              event->ReactEvent.Synthetic.preventDefault;
              ReasonReactRouter.push(href);
            }
          )>
          (ReasonReact.array(children))
        </a>;
      },
    };
  };
};
