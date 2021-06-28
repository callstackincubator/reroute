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
    [@react.component]
    let make = (~children) => {
      let (state, dispatch) =
        React.useReducer(
          (_state, action) =>
            switch (action) {
            | ChangeRoute(route) => route
            },
          ReasonReactRouter.dangerouslyGetInitialUrl() |> Config.routeFromUrl,
        );
      React.useEffect0(() => {
        let watcherID =
          ReasonReactRouter.watchUrl(url =>
            dispatch(ChangeRoute(url |> Config.routeFromUrl))
          );
        Some(() => ReasonReactRouter.unwatchUrl(watcherID));
      });
      children(~currentRoute=state);
    };
  };
  module Link = {
    [@react.component]
    let make = (~route, ~children) => {
      let href = Config.routeToUrl(route);
      <a
        href
        onClick={event => {
          event->ReactEvent.Synthetic.preventDefault;
          ReasonReactRouter.push(href);
        }}>
        children
      </a>;
    };
  };
};
