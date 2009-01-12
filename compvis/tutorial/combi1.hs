import EasyVision

camera = findSize >>= getCam 0 ~> rgb . channels
observe winname = monitor winname (mpSize 20) drawImage
run c = prepare >> (c >>= launch . (>> return ()))

grid n = map (blockImage . partit n) . partit (n*n) . map (resize (mpSize 4))
    where partit _ [] = []
          partit k l = take k l : partit k (drop k l)

main = run $   camera
           >>= observe "original"
           ~~> grid 2
           >>= observe "first grid"
           ~~> grid 3
           >>= observe "second grid"
