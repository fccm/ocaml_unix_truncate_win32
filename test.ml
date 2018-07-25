
external my_truncate : string -> int -> unit = "my_truncate"

let () =
  my_truncate "test.txt" 3;
;;

