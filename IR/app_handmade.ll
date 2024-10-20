; ModuleID = 'app.c'
source_filename = "app.c"

declare void @simPutSpring(i32, i32, i32, i32)

declare void @simFlush(void)

declare i32 @simGetPixel(i32, i32)

declare i32 @simGetLength(i32, i32)

declare i32 @simRand(i32, i32)

declare void @simPutPixel(i32, i32, i32)

declare i32 @simMixColors(i32, i32, i32, i32)

define void @app() {
  call void @simPutSpring(i32 10, i32 2, i32 -16711936, i32 1)
  call void @simPutSpring(i32 25, i32 20, i32 -16711936, i32 1)
  call void @simPutSpring(i32 50, i32 30, i32 -16711936, i32 1)
  call void @simPutSpring(i32 75, i32 50, i32 -16711936, i32 1)
  call void @simPutSpring(i32 100, i32 10, i32 -16711936, i32 1)
  call void @simFlush()
  br label %1

1:                                                ; preds = %7, %0
  %2 = phi i32 [ 0, %0 ], [ %8, %7 ]
  br label %4

3:                                                ; preds = %7
  ret void

4:                                                ; preds = %10, %1
  %5 = phi i32 [ 0, %1 ], [ %11, %10 ]
  %6 = sub nuw nsw i32 64, %5
  br label %13

7:                                                ; preds = %10
  call void @simFlush()
  %8 = add nuw nsw i32 %2, 1
  %9 = icmp eq i32 %8, 200
  br i1 %9, label %3, label %1

10:                                               ; preds = %32
  %11 = add nuw nsw i32 %5, 1
  %12 = icmp eq i32 %11, 64
  br i1 %12, label %7, label %4

13:                                               ; preds = %32, %4
  %14 = phi i32 [ 0, %4 ], [ %33, %32 ]
  %15 = call i32 @simGetPixel(i32 %14, i32 %5)
  %16 = call i32 @simGetLength(i32 %14, i32 %5)
  %17 = icmp eq i32 %15, -16711936
  %18 = icmp sgt i32 %16, 0
  %19 = select i1 %17, i1 %18, i32 0
  br i1 %19, label %20, label %32

20:                                               ; preds = %13
  %21 = call i32 @simRand(i32 -1, i32 1)
  %22 = call i32 @simRand(i32 1, i32 1)
  %23 = mul nsw i32 %21, %16
  %24 = add nsw i32 %23, %14
  %25 = mul nsw i32 %22, %16
  %26 = add nsw i32 %25, %5
  %27 = call i32 @simMixColors(i32 -16711936, i32 -16751104, i32 %5, i32 %6)
  call void @simPutPixel(i32 %24, i32 %26, i32 %27)
  %28 = call i32 @simRand(i32 -1, i32 1)
  %29 = mul nsw i32 %28, %16
  %30 = add nsw i32 %29, %14
  %31 = call i32 @simRand(i32 1, i32 %16)
  call void @simPutSpring(i32 %30, i32 %26, i32 -16711936, i32 %31)
  br label %32

32:                                               ; preds = %20, %13
  %33 = add nuw nsw i32 %14, 1
  %34 = icmp eq i32 %33, 128
  br i1 %34, label %10, label %13
}
