[@react.component]
let make = () => {
  <div>
    <h1> {React.string("We are sorry...")} </h1>
    <p>
      {React.string(
         "Unfortunately we could not find the page you were looking for.",
       )}
    </p>
    <p>
      {React.string("Use the above menu to navigate to other pages :)")}
    </p>
  </div>;
};
