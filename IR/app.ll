; ModuleID = 'app.c'
source_filename = "app.c"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-pc-linux-gnu"

; Function Attrs: nounwind uwtable
define dso_local void @app() local_unnamed_addr #0 {
  tail call void @simPutSpring(i32 noundef 10, i32 noundef 2, i32 noundef -16711936, i32 noundef 1) #2
  tail call void @simPutSpring(i32 noundef 50, i32 noundef 30, i32 noundef -16711936, i32 noundef 1) #2
  tail call void @simPutSpring(i32 noundef 100, i32 noundef 10, i32 noundef -16711936, i32 noundef 1) #2
  tail call void (...) @simFlush() #2
  br label %1

1:                                                ; preds = %0, %7
  %2 = phi i32 [ 0, %0 ], [ %8, %7 ]
  br label %4

3:                                                ; preds = %7
  ret void

4:                                                ; preds = %1, %10
  %5 = phi i32 [ 0, %1 ], [ %11, %10 ]
  %6 = sub nuw nsw i32 64, %5
  br label %13

7:                                                ; preds = %10
  tail call void (...) @simFlush() #2
  %8 = add nuw nsw i32 %2, 1
  %9 = icmp eq i32 %8, 400
  br i1 %9, label %3, label %1, !llvm.loop !5

10:                                               ; preds = %32
  %11 = add nuw nsw i32 %5, 1
  %12 = icmp eq i32 %11, 64
  br i1 %12, label %7, label %4, !llvm.loop !7

13:                                               ; preds = %4, %32
  %14 = phi i32 [ 0, %4 ], [ %33, %32 ]
  %15 = tail call i32 @simGetPixel(i32 noundef %14, i32 noundef %5) #2
  %16 = tail call i32 @simGetLength(i32 noundef %14, i32 noundef %5) #2
  %17 = icmp eq i32 %15, -16711936
  %18 = icmp sgt i32 %16, 0
  %19 = select i1 %17, i1 %18, i1 false
  br i1 %19, label %20, label %32

20:                                               ; preds = %13
  tail call void @simPutPixel(i32 noundef %14, i32 noundef %5, i32 noundef -3308225) #2
  %21 = tail call i32 @simRand(i32 noundef -1, i32 noundef 1) #2
  %22 = tail call i32 @simRand(i32 noundef 1, i32 noundef 1) #2
  %23 = mul nsw i32 %21, %16
  %24 = add nsw i32 %23, %14
  %25 = mul nsw i32 %22, %16
  %26 = add nsw i32 %25, %5
  %27 = tail call i32 @simMixColors(i32 noundef -16711936, i32 noundef -16751104, i32 noundef %5, i32 noundef %6) #2
  tail call void @simPutPixel(i32 noundef %24, i32 noundef %26, i32 noundef %27) #2
  %28 = tail call i32 @simRand(i32 noundef -1, i32 noundef 1) #2
  %29 = mul nsw i32 %28, %16
  %30 = add nsw i32 %29, %14
  %31 = tail call i32 @simRand(i32 noundef 1, i32 noundef %16) #2
  tail call void @simPutSpring(i32 noundef %30, i32 noundef %26, i32 noundef -16711936, i32 noundef %31) #2
  br label %32

32:                                               ; preds = %20, %13
  %33 = add nuw nsw i32 %14, 1
  %34 = icmp eq i32 %33, 128
  br i1 %34, label %10, label %13, !llvm.loop !8
}

declare void @simPutSpring(i32 noundef, i32 noundef, i32 noundef, i32 noundef) local_unnamed_addr #1

declare void @simFlush(...) local_unnamed_addr #1

declare i32 @simGetPixel(i32 noundef, i32 noundef) local_unnamed_addr #1

declare i32 @simGetLength(i32 noundef, i32 noundef) local_unnamed_addr #1

declare void @simPutPixel(i32 noundef, i32 noundef, i32 noundef) local_unnamed_addr #1

declare i32 @simRand(i32 noundef, i32 noundef) local_unnamed_addr #1

declare i32 @simMixColors(i32 noundef, i32 noundef, i32 noundef, i32 noundef) local_unnamed_addr #1

attributes #0 = { nounwind uwtable "frame-pointer"="none" "min-legal-vector-width"="0" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #1 = { "frame-pointer"="none" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #2 = { nounwind }

!llvm.module.flags = !{!0, !1, !2, !3}
!llvm.ident = !{!4}

!0 = !{i32 1, !"wchar_size", i32 4}
!1 = !{i32 7, !"PIC Level", i32 2}
!2 = !{i32 7, !"PIE Level", i32 2}
!3 = !{i32 7, !"uwtable", i32 1}
!4 = !{!"Ubuntu clang version 14.0.0-1ubuntu1.1"}
!5 = distinct !{!5, !6}
!6 = !{!"llvm.loop.mustprogress"}
!7 = distinct !{!7, !6}
!8 = distinct !{!8, !6}
