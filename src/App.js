import React, { useRef, useEffect, useState } from "react";

const App = () => {
  const canvasRef = useRef();

  const [mousePos, setMousePos] = useState({
    x: 0,
    y: 0,
    lastX: 0,
    lastY: 0
  });

  const [mouseDown, setMouseDown] = useState(false);

  const handleMove = e => {
    setMousePos({
      x: e.layerX,
      y: e.layerY,
      lastX: mousePos.x,
      lastY: mousePos.y
    });
  };

  const handleDown = () => setMouseDown(true);

  const handleUp = () => setMouseDown(false);

  useEffect(() => {
    const canvasInitial = canvasRef.current;
    canvasInitial.addEventListener("mousemove", handleMove);
    canvasInitial.addEventListener("mousedown", handleDown);
    canvasInitial.addEventListener("mouseup", handleUp);
    return () => {
      canvasInitial.removeEventListener("mousemove", handleMove);
      canvasInitial.removeEventListener("mousedown", handleDown);
      canvasInitial.removeEventListener("mouseup", handleUp);
    };
  }, []);

  useEffect(() => {
    if (mouseDown) {
      const ctx = canvasRef.current.getContext("2d");
      ctx.lineWidth = 8;
      ctx.moveTo(0, 0);
      ctx.lineTo(mousePos.x, mousePos.y);
      ctx.stroke();
    }
  }, [mousePos]);

  console.log(mousePos);

  return (
    <canvas
      style={{ border: "1px solid black" }}
      width="280"
      height="280"
      ref={canvasRef}
    />
  );
};

export default App;
