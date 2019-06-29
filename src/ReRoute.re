module type RouterConfig = {
  type route;
  let routeFromUrl: ReasonReact.Router.url => route;
  let routeToUrl: route => string;
};

module CreateRouter = (Config: RouterConfig) => {
  let useRouter = () => {
    let (currentRoute: Config.route, setCurrentRoute) =
      React.useState(() =>
        ReasonReact.Router.dangerouslyGetInitialUrl() |> Config.routeFromUrl
      );
    React.useEffect1(
      () => {
        let watcherID =
          ReasonReact.Router.watchUrl(url =>
            setCurrentRoute(_old => url |> Config.routeFromUrl)
          );
        Some(() => ReasonReact.Router.unwatchUrl(watcherID));
      },
      [||],
    );
    currentRoute;
  };

  module Container = {
    [@react.component]
    let make = (~children) => {
      let currentRoute = useRouter();
      children(~currentRoute);
    };

    module Jsx2 = {
      let component = ReasonReact.statelessComponent("RouterContainer");

      let make = children =>
        ReasonReactCompat.wrapReactForReasonReact(
          make,
          makeProps(~children, ()),
          children,
        );
    };
  };
  module Link = {
    [@react.component]
    let make = (~route, ~className=?, ~children) => {
      let href = Config.routeToUrl(route);
      <a
        href
        ?className
        onClick={
          event => {
            event->ReactEvent.Synthetic.preventDefault;
            ReasonReact.Router.push(href);
          }
        }>
        children
      </a>;
    };

    module Jsx2 = {
      let component = ReasonReact.statelessComponent("Link");

      let make =
          (~route, ~className=?, children: array(ReasonReact.reactElement)) =>
        ReasonReactCompat.wrapReactForReasonReact(
          make,
          makeProps(
            ~route,
            ~className?,
            ~children=React.array(children),
            (),
          ),
          React.array(children),
        );
    };
  };
};
