document.addEventListener("DOMContentLoaded", () => {
    /* ------------------------------
       1. Custom Cursor
       ------------------------------ */
    const dot = document.querySelector(".cursor-dot");
    const outline = document.querySelector(".cursor-outline");

    if (dot && outline && window.innerWidth > 768) {
        let mouseX = 0;
        let mouseY = 0;
        let outlineX = 0;
        let outlineY = 0;

        window.addEventListener("mousemove", (e) => {
            mouseX = e.clientX;
            mouseY = e.clientY;
            dot.style.left = `${mouseX}px`;
            dot.style.top = `${mouseY}px`;
        });

        // Smooth follow for the outline
        const animateOutline = () => {
            let distX = mouseX - outlineX;
            let distY = mouseY - outlineY;
            outlineX += distX * 0.2;
            outlineY += distY * 0.2;
            
            outline.style.left = `${outlineX}px`;
            outline.style.top = `${outlineY}px`;
            
            requestAnimationFrame(animateOutline);
        };
        animateOutline();

        // Hover effects on interactive elements
        const interactives = document.querySelectorAll("a, button, .btn-premium, .hero-img-card, .nav-link, input, textarea");
        interactives.forEach(el => {
            el.addEventListener("mouseenter", () => {
                document.body.classList.add("cursor-hover");
            });
            el.addEventListener("mouseleave", () => {
                document.body.classList.remove("cursor-hover");
            });
        });
    }

    /* ------------------------------
       2. Typing Effect (Two-line sequential)
       ------------------------------ */
    const line1El = document.getElementById("typing-line1");
    const line2El = document.getElementById("typing-line2");
    const cursorEl = document.getElementById("typing-cursor");

    if (line1El && line2El && cursorEl) {
        const line1Text = "Développeur Web";
        const line2Text = "Front-End (React) | Flask";

        // Clear text for animation (HTML fallback was visible until now)
        line1El.textContent = "";
        line2El.textContent = "";

        // Move cursor next to line1 initially
        line1El.insertAdjacentElement("afterend", cursorEl);
        // Place cursor right after line1 (before the <br>)
        line1El.parentNode.insertBefore(cursorEl, line1El.nextSibling);

        let charIndex = 0;
        let currentLine = 1;

        const typeLine = () => {
            if (currentLine === 1) {
                if (charIndex < line1Text.length) {
                    line1El.textContent = line1Text.substring(0, charIndex + 1);
                    charIndex++;
                    setTimeout(typeLine, 80);
                } else {
                    // Line 1 done — move cursor to after line2
                    line2El.insertAdjacentElement("afterend", cursorEl);
                    charIndex = 0;
                    currentLine = 2;
                    setTimeout(typeLine, 400); // Pause between lines
                }
            } else if (currentLine === 2) {
                if (charIndex < line2Text.length) {
                    line2El.textContent = line2Text.substring(0, charIndex + 1);
                    charIndex++;
                    setTimeout(typeLine, 80);
                } else {
                    // All done — stop cursor blinking after a short delay
                    setTimeout(() => {
                        cursorEl.classList.add("typing-done");
                    }, 1500);
                }
            }
        };

        // Start typing after initial delay
        setTimeout(typeLine, 1000);
    }

    /* ------------------------------
       3. Particles Background
       ------------------------------ */
    const canvas = document.getElementById("hero-particles");
    if (canvas) {
        const ctx = canvas.getContext("2d");
        let particlesArray = [];

        // Set canvas size
        const setCanvasSize = () => {
            const parent = canvas.parentElement;
            canvas.width = parent.offsetWidth;
            canvas.height = parent.offsetHeight;
        };
        setCanvasSize();

        window.addEventListener('resize', () => {
            setCanvasSize();
            initParticles();
        });

        class Particle {
            constructor(x, y, directionX, directionY, size, color) {
                this.x = x;
                this.y = y;
                this.directionX = directionX;
                this.directionY = directionY;
                this.size = size;
                this.color = color;
            }
            draw() {
                ctx.beginPath();
                ctx.arc(this.x, this.y, this.size, 0, Math.PI * 2, false);
                ctx.fillStyle = this.color;
                ctx.fill();
            }
            update() {
                if (this.x > canvas.width || this.x < 0) {
                    this.directionX = -this.directionX;
                }
                if (this.y > canvas.height || this.y < 0) {
                    this.directionY = -this.directionY;
                }
                this.x += this.directionX;
                this.y += this.directionY;
                this.draw();
            }
        }

        function initParticles() {
            particlesArray = [];
            // Calculate number of particles based on screen size but keep it minimal
            let numberOfParticles = Math.floor((canvas.height * canvas.width) / 18000);
            if (numberOfParticles > 60) numberOfParticles = 60; // Max particles to maintain performance and readability

            for (let i = 0; i < numberOfParticles; i++) {
                let size = (Math.random() * 2) + 1;
                let x = (Math.random() * ((canvas.width - size * 2) - (size * 2)) + size * 2);
                let y = (Math.random() * ((canvas.height - size * 2) - (size * 2)) + size * 2);
                let directionX = (Math.random() * 0.5) - 0.25;
                let directionY = (Math.random() * 0.5) - 0.25;
                // Green/Teal tones matching the design
                let color = 'rgba(0, 200, 150, 0.5)';

                particlesArray.push(new Particle(x, y, directionX, directionY, size, color));
            }
        }

        function animateParticles() {
            requestAnimationFrame(animateParticles);
            ctx.clearRect(0, 0, canvas.width, canvas.height);

            for (let i = 0; i < particlesArray.length; i++) {
                particlesArray[i].update();
            }
            connectParticles();
        }

        function connectParticles() {
            let opacityValue = 1;
            for (let a = 0; a < particlesArray.length; a++) {
                for (let b = a; b < particlesArray.length; b++) {
                    let distance = ((particlesArray[a].x - particlesArray[b].x) * (particlesArray[a].x - particlesArray[b].x)) +
                                   ((particlesArray[a].y - particlesArray[b].y) * (particlesArray[a].y - particlesArray[b].y));
                    if (distance < (canvas.width / 8) * (canvas.height / 8)) {
                        opacityValue = 1 - (distance / 20000);
                        // Green/Teal lines
                        ctx.strokeStyle = `rgba(0, 200, 150, ${opacityValue * 0.2})`;
                        ctx.lineWidth = 1;
                        ctx.beginPath();
                        ctx.moveTo(particlesArray[a].x, particlesArray[a].y);
                        ctx.lineTo(particlesArray[b].x, particlesArray[b].y);
                        ctx.stroke();
                    }
                }
            }
        }

        initParticles();
        animateParticles();
    }
});
