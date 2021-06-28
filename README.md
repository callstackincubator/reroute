# reroute

> a fast, declarative microrouter for reason-react

## Getting started

### Installation

Open a Terminal in your project's folder and run,

```
$ yarn add reason-reroute
```

After installation, you will need to add this library to your `bsconfig.json` dependencies

```
"bs-dependencies": [
  "reason-react",
  "reason-reroute"
],
```

## Usage

```reason
module RouterConfig = {
  type route =
    | Admin
    | Home;
  let routeFromUrl = (url: ReasonReactRouter.url) =>
    switch url.path {
    | ["admin"] => Admin
    | [] => Home
    };
  let routeToUrl = (route: route) =>
    switch route {
    | Admin => "/admin"
    | Home => "/"
    };
};

module Router = ReRoute.CreateRouter(RouterConfig);

[@react.component]
let make = ()=> {

    <Router.Container>
      ...(
           (~currentRoute) =>
             switch currentRoute {
             | RouterConfig.Admin => <Admin />
             | RouterConfig.Home => <Home />
             }
         )
    </Router.Container>
};
```

## API

Sections below are under construction.

### Link

### Container

## Rationale

ReasonReact comes with a router ([`ReasonReactRouter`](https://reasonml.github.io/reason-react/docs/en/router.html)) by default. It offers minimal yet powerful API that is suitable for applications at any scale. However, being just an API, it leaves the routing logic up to the developer. This library builds on top of it to provide an elegant interface for working with routes that is ready to use, predictable and consistent across apps you create.

## Credits

The concept of `reroute` has been highly influenced by [@thangngoc89](https://github.com/thangngoc89) and his [reference implementation](https://gist.github.com/thangngoc89/c9162c0263df5427fe9a36fc7f94ac94). Thank you for pushing this forward!

## License

MIT (c) 2018 Callstack
