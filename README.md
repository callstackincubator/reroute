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

```
type route =
  | Admin
  | Home;

let routeFromUrl = (url: ReasonReact.Router.url) =>
  switch url.path {
  | ["admin"] => Admin
  | [] => Home
  };

let routeToUrl = (route: t) =>
  switch route {
  | Admin => "/admin"
  | Home => "/"
  };

module Router =
  ReRoute.CreateRouter(
    {
      type route = route;
      let routeFromUrl = routeFromUrl;
      let routeToUrl = routeToUrl;
    }
  );

let component = ReasonReact.statelessComponent("App");

let make = _children => {
  ...component,
  render: _self =>
    <Router.Container>
      ...(
           (~currentRoute) =>
             switch currentRoute {
             | Route.Admin => <Admin />
             | Route.Home => <Home />
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

## Credits

The concept of `reroute` has been highly influenced by [@thangngoc89](https://github.com/thangngoc89) and his [reference implementation](https://gist.github.com/thangngoc89/c9162c0263df5427fe9a36fc7f94ac94). Thank you for pushing this forward!  

## License

MIT (c) 2018 Callstack
